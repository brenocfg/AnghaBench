#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* method_name; size_t method_size; void* method_load_address; int /*<<< orphan*/ * source_file_name; int /*<<< orphan*/ * class_file_name; int /*<<< orphan*/  method_id; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ iJIT_Method_Load ;

/* Variables and functions */
 int /*<<< orphan*/  iJIT_GetNewMethodID () ; 
 scalar_t__ iJIT_IsProfilingActive () ; 
 int /*<<< orphan*/  iJIT_NotifyEvent (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ iJIT_SAMPLING_ON ; 
 int /*<<< orphan*/  iJVM_EVENT_TYPE_METHOD_LOAD_FINISHED ; 

__attribute__((used)) static void zend_jit_vtune_register(const char *name,
                                    const void *start,
                                    size_t      size)
{
	iJIT_Method_Load jmethod = {0};

	if (iJIT_IsProfilingActive() != iJIT_SAMPLING_ON) {
		return;
	}

	jmethod.method_id = iJIT_GetNewMethodID();
	jmethod.method_name = (char*)name;
	jmethod.class_file_name = NULL;
	jmethod.source_file_name = NULL;
	jmethod.method_load_address = (void*)start;
	jmethod.method_size = size;

	iJIT_NotifyEvent(iJVM_EVENT_TYPE_METHOD_LOAD_FINISHED, (void*)&jmethod);
}