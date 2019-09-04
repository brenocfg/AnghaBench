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
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/ * LPPROC_THREAD_ATTRIBUTE_LIST ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  InitializeProcThreadAttributeList (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROC_THREAD_ATTRIBUTE_HANDLE_LIST ; 
 int /*<<< orphan*/  UpdateProcThreadAttribute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_handle_list ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_set_destructor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * talloc_size (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LPPROC_THREAD_ATTRIBUTE_LIST create_handle_list(void *ctx,
                                                       HANDLE *handles, int num)
{
    // Get required attribute list size
    SIZE_T size = 0;
    if (!InitializeProcThreadAttributeList(NULL, 1, 0, &size)) {
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
            return NULL;
    }

    // Allocate attribute list
    LPPROC_THREAD_ATTRIBUTE_LIST list = talloc_size(ctx, size);
    if (!InitializeProcThreadAttributeList(list, 1, 0, &size))
        goto error;
    talloc_set_destructor(list, delete_handle_list);

    if (!UpdateProcThreadAttribute(list, 0, PROC_THREAD_ATTRIBUTE_HANDLE_LIST,
                                   handles, num * sizeof(HANDLE), NULL, NULL))
        goto error;

    return list;
error:
    talloc_free(list);
    return NULL;
}