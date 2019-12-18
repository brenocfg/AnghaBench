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
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int MAX_BUFSIZE ; 
 int MAX_CATCH_RADIUS ; 
 int MIN_BUFFERS ; 
 int MIN_BUFSIZE ; 
 int catchRadius ; 
 char* get_options (char*,int /*<<< orphan*/ ,int*) ; 
 int numWriteBufs ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int writeBufSize ; 

__attribute__((used)) static int dmasound_setup(char *str)
{
	int ints[6], size;

	str = get_options(str, ARRAY_SIZE(ints), ints);

	/* check the bootstrap parameter for "dmasound=" */

	/* FIXME: other than in the most naive of cases there is no sense in these
	 *	  buffers being other than powers of two.  This is not checked yet.
	 */

	switch (ints[0]) {
	case 3:
		if ((ints[3] < 0) || (ints[3] > MAX_CATCH_RADIUS))
			printk("dmasound_setup: invalid catch radius, using default = %d\n", catchRadius);
		else
			catchRadius = ints[3];
		/* fall through */
	case 2:
		if (ints[1] < MIN_BUFFERS)
			printk("dmasound_setup: invalid number of buffers, using default = %d\n", numWriteBufs);
		else
			numWriteBufs = ints[1];
		/* fall through */
	case 1:
		if ((size = ints[2]) < 256) /* check for small buffer specs */
			size <<= 10 ;
                if (size < MIN_BUFSIZE || size > MAX_BUFSIZE)
                        printk("dmasound_setup: invalid write buffer size, using default = %d\n", writeBufSize);
                else
                        writeBufSize = size;
	case 0:
		break;
	default:
		printk("dmasound_setup: invalid number of arguments\n");
		return 0;
	}
	return 1;
}