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

/* Variables and functions */
 int /*<<< orphan*/  InitializeSecurityDescriptor (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_MIN_LENGTH ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_REVISION ; 
 int /*<<< orphan*/  SetSecurityDescriptorDacl (void*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *create_full_access_security_descriptor()
{
	void *sd = malloc(SECURITY_DESCRIPTOR_MIN_LENGTH);
	if (!sd) {
		return NULL;
	}

	if (!InitializeSecurityDescriptor(sd, SECURITY_DESCRIPTOR_REVISION)) {
		goto error;
	}

	if (!SetSecurityDescriptorDacl(sd, true, NULL, false)) {
		goto error;
	}

	return sd;

error:
	free(sd);
	return NULL;
}