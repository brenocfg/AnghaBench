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
struct osd_external {int /*<<< orphan*/  ass; int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_ass_renderer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_external(struct osd_external *ext)
{
    talloc_free(ext->text);
    destroy_ass_renderer(&ext->ass);
}