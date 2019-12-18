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
struct handle_wrapper {scalar_t__ size; int /*<<< orphan*/  lock; int /*<<< orphan*/  hglobal; } ;
typedef  scalar_t__ ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 void* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,char*,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static ULONG handle_read(struct handle_wrapper *handle, ULONG *pos, void *dest, ULONG len)
{
    void *source;

    EnterCriticalSection(&handle->lock);

    if (*pos < handle->size)
        len = min(handle->size - *pos, len);
    else
        len = 0;

    source = GlobalLock(handle->hglobal);
    if (source)
    {
        memcpy(dest, (char *)source + *pos, len);
        *pos += len;
        GlobalUnlock(handle->hglobal);
    }
    else
    {
        WARN("read from invalid hglobal %p\n", handle->hglobal);
        len = 0;
    }

    LeaveCriticalSection(&handle->lock);
    return len;
}