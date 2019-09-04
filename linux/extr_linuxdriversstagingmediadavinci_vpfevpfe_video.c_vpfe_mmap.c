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
struct vpfe_video_device {int /*<<< orphan*/  buffer_queue; struct vpfe_device* vpfe_dev; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct vm_area_struct {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int vb2_mmap (int /*<<< orphan*/ *,struct vm_area_struct*) ; 
 struct vpfe_video_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vpfe_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct vpfe_video_device *video = video_drvdata(file);
	struct vpfe_device *vpfe_dev = video->vpfe_dev;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_mmap\n");
	return vb2_mmap(&video->buffer_queue, vma);
}