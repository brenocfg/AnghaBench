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
struct zr36016 {int /*<<< orphan*/  num; int /*<<< orphan*/  name; } ;
struct videocodec {struct zr36016* data; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct zr36016*) ; 
 int /*<<< orphan*/  zr36016_codecs ; 

__attribute__((used)) static int
zr36016_unset (struct videocodec *codec)
{
	struct zr36016 *ptr = codec->data;

	if (ptr) {
		/* do wee need some codec deinit here, too ???? */

		dprintk(1, "%s: finished codec #%d\n", ptr->name,
			ptr->num);
		kfree(ptr);
		codec->data = NULL;

		zr36016_codecs--;
		return 0;
	}

	return -EFAULT;
}