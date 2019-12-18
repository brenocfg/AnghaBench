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
struct smack_known {int dummy; } ;
struct file {scalar_t__ f_security; } ;
struct TYPE_2__ {scalar_t__ lbs_file; } ;

/* Variables and functions */
 TYPE_1__ smack_blob_sizes ; 

__attribute__((used)) static inline struct smack_known **smack_file(const struct file *file)
{
	return (struct smack_known **)(file->f_security +
				       smack_blob_sizes.lbs_file);
}