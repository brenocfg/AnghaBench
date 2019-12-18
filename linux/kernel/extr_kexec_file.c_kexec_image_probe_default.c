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
struct kimage {struct kexec_file_ops* fops; } ;
struct kexec_file_ops {int (* probe ) (void*,unsigned long) ;} ;

/* Variables and functions */
 int ENOEXEC ; 
 struct kexec_file_ops** kexec_file_loaders ; 
 int stub1 (void*,unsigned long) ; 

int kexec_image_probe_default(struct kimage *image, void *buf,
			      unsigned long buf_len)
{
	const struct kexec_file_ops * const *fops;
	int ret = -ENOEXEC;

	for (fops = &kexec_file_loaders[0]; *fops && (*fops)->probe; ++fops) {
		ret = (*fops)->probe(buf, buf_len);
		if (!ret) {
			image->fops = *fops;
			return ret;
		}
	}

	return ret;
}