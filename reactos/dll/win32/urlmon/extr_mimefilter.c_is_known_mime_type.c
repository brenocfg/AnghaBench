#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  mime; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* mime_filters ; 
 TYPE_1__* mime_filters_any_pos ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL is_known_mime_type(const WCHAR *mime)
{
    unsigned i;

    for(i=0; i < ARRAY_SIZE(mime_filters_any_pos); i++) {
        if(!strcmpW(mime, mime_filters_any_pos[i].mime))
            return TRUE;
    }

    for(i=0; i < ARRAY_SIZE(mime_filters); i++) {
        if(!strcmpW(mime, mime_filters[i].mime))
            return TRUE;
    }

    return FALSE;
}