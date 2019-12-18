#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  image; struct TYPE_9__* next; struct TYPE_9__* images; struct TYPE_9__* partstate; struct TYPE_9__* properties; struct TYPE_9__* classes; scalar_t__ hTheme; int /*<<< orphan*/  dwRefCount; } ;
typedef  TYPE_1__* PTHEME_PROPERTY ;
typedef  TYPE_1__* PTHEME_PARTSTATE ;
typedef  TYPE_1__* PTHEME_IMAGE ;
typedef  TYPE_1__* PTHEME_FILE ;
typedef  TYPE_1__* PTHEME_CLASS ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 

void MSSTYLES_CloseThemeFile(PTHEME_FILE tf)
{
    if(tf) {

        tf->dwRefCount--;
        TRACE("Theme %p refcount: %d\n", tf, tf->dwRefCount);

        if(!tf->dwRefCount) {
            if(tf->hTheme) FreeLibrary(tf->hTheme);
            if(tf->classes) {
                while(tf->classes) {
                    PTHEME_CLASS pcls = tf->classes;
                    tf->classes = pcls->next;
                    while(pcls->partstate) {
                        PTHEME_PARTSTATE ps = pcls->partstate;

                        while(ps->properties) {
                            PTHEME_PROPERTY prop = ps->properties;
                            ps->properties = prop->next;
                            HeapFree(GetProcessHeap(), 0, prop);
                        }

                        pcls->partstate = ps->next;
                        HeapFree(GetProcessHeap(), 0, ps);
                    }
                    HeapFree(GetProcessHeap(), 0, pcls);
                }
            }
            while (tf->images)
            {
                PTHEME_IMAGE img = tf->images;
                tf->images = img->next;
                DeleteObject (img->image);
                HeapFree (GetProcessHeap(), 0, img);
            }
            HeapFree(GetProcessHeap(), 0, tf);
        }
    }
}