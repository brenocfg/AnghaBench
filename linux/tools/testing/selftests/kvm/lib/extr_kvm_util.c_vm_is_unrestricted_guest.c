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
struct kvm_vm {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* KVM_DEV_PATH ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 

bool vm_is_unrestricted_guest(struct kvm_vm *vm)
{
	char val = 'N';
	size_t count;
	FILE *f;

	if (vm == NULL) {
		/* Ensure that the KVM vendor-specific module is loaded. */
		f = fopen(KVM_DEV_PATH, "r");
		TEST_ASSERT(f != NULL, "Error in opening KVM dev file: %d",
			    errno);
		fclose(f);
	}

	f = fopen("/sys/module/kvm_intel/parameters/unrestricted_guest", "r");
	if (f) {
		count = fread(&val, sizeof(char), 1, f);
		TEST_ASSERT(count == 1, "Unable to read from param file.");
		fclose(f);
	}

	return val == 'Y';
}