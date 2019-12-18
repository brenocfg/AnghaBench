#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hMF; } ;
typedef  TYPE_1__ METAFILEPICT ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ ) ; 
 TYPE_1__* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_metafilepict(HGLOBAL src)
{
    METAFILEPICT *src_ptr;

    src_ptr = GlobalLock(src);
    if (src_ptr)
    {
        DeleteMetaFile(src_ptr->hMF);
        GlobalUnlock(src);
    }
    GlobalFree(src);
}