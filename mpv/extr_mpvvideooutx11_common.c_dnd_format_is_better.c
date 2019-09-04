#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vo_x11_state {int /*<<< orphan*/  input_ctx; } ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 int mp_event_get_mime_type_score (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x11_dnd_mime_type (struct vo_x11_state*,scalar_t__) ; 

__attribute__((used)) static bool dnd_format_is_better(struct vo_x11_state *x11, Atom cur, Atom new)
{
    int new_score = mp_event_get_mime_type_score(x11->input_ctx,
                                                 x11_dnd_mime_type(x11, new));
    int cur_score = -1;
    if (cur) {
        cur_score = mp_event_get_mime_type_score(x11->input_ctx,
                                                 x11_dnd_mime_type(x11, cur));
    }
    return new_score >= 0 && new_score > cur_score;
}