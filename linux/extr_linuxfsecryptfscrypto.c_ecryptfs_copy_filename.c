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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

__attribute__((used)) static int ecryptfs_copy_filename(char **copied_name, size_t *copied_name_size,
				  const char *name, size_t name_size)
{
	int rc = 0;

	(*copied_name) = kmalloc((name_size + 1), GFP_KERNEL);
	if (!(*copied_name)) {
		rc = -ENOMEM;
		goto out;
	}
	memcpy((void *)(*copied_name), (void *)name, name_size);
	(*copied_name)[(name_size)] = '\0';	/* Only for convenience
						 * in printing out the
						 * string in debug
						 * messages */
	(*copied_name_size) = name_size;
out:
	return rc;
}