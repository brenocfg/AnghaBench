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
struct cifs_fid {int /*<<< orphan*/  lease_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  generate_random_uuid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
smb2_new_lease_key(struct cifs_fid *fid)
{
	generate_random_uuid(fid->lease_key);
}