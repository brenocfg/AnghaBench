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
struct fs3270 {int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct fs3270* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fs3270*) ; 
 struct fs3270* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3270_request_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fs3270 *
fs3270_alloc_view(void)
{
	struct fs3270 *fp;

	fp = kzalloc(sizeof(struct fs3270),GFP_KERNEL);
	if (!fp)
		return ERR_PTR(-ENOMEM);
	fp->init = raw3270_request_alloc(0);
	if (IS_ERR(fp->init)) {
		kfree(fp);
		return ERR_PTR(-ENOMEM);
	}
	return fp;
}