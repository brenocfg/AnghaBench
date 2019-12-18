#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_6__ {int buffer_size; scalar_t__ hloc32W; } ;
typedef  scalar_t__ HLOCAL ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_LockBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_NOTIFY_PARENT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_UnlockBuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EN_ERRSPACE ; 
 int /*<<< orphan*/  FALSE ; 
 int LMEM_MOVEABLE ; 
 int LMEM_ZEROINIT ; 
 scalar_t__ LocalReAlloc (scalar_t__,int,int) ; 
 int LocalSize (scalar_t__) ; 
 int ROUND_TO_GROW (int) ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int) ; 

__attribute__((used)) static BOOL EDIT_MakeFit(EDITSTATE *es, UINT size)
{
	HLOCAL hNew32W;

	if (size <= es->buffer_size)
		return TRUE;

	TRACE("trying to ReAlloc to %d+1 characters\n", size);

        /* Force edit to unlock its buffer. es->text now NULL */
	EDIT_UnlockBuffer(es, TRUE);

	if (es->hloc32W) {
	    UINT alloc_size = ROUND_TO_GROW((size + 1) * sizeof(WCHAR));
	    if ((hNew32W = LocalReAlloc(es->hloc32W, alloc_size, LMEM_MOVEABLE | LMEM_ZEROINIT))) {
		TRACE("Old 32 bit handle %p, new handle %p\n", es->hloc32W, hNew32W);
		es->hloc32W = hNew32W;
		es->buffer_size = LocalSize(hNew32W)/sizeof(WCHAR) - 1;
	    }
	}

	EDIT_LockBuffer(es);

	if (es->buffer_size < size) {
		WARN("FAILED !  We now have %d+1\n", es->buffer_size);
		EDIT_NOTIFY_PARENT(es, EN_ERRSPACE);
		return FALSE;
	} else {
		TRACE("We now have %d+1\n", es->buffer_size);
		return TRUE;
	}
}