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
struct zr36016 {int /*<<< orphan*/  name; } ;
struct videocodec {scalar_t__ data; } ;

/* Variables and functions */
#define  CODEC_G_CODEC_MODE 133 
#define  CODEC_G_STATUS 132 
#define  CODEC_G_VFE 131 
#define  CODEC_S_CODEC_MODE 130 
#define  CODEC_S_MMAP 129 
#define  CODEC_S_VFE 128 
 int EFAULT ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
zr36016_control (struct videocodec *codec,
		 int                type,
		 int                size,
		 void              *data)
{
	struct zr36016 *ptr = (struct zr36016 *) codec->data;
	int *ival = (int *) data;

	dprintk(2, "%s: control %d call with %d byte\n", ptr->name, type,
		size);

	switch (type) {
	case CODEC_G_STATUS:	/* get last status - we don't know it ... */
		if (size != sizeof(int))
			return -EFAULT;
		*ival = 0;
		break;

	case CODEC_G_CODEC_MODE:
		if (size != sizeof(int))
			return -EFAULT;
		*ival = 0;
		break;

	case CODEC_S_CODEC_MODE:
		if (size != sizeof(int))
			return -EFAULT;
		if (*ival != 0)
			return -EINVAL;
		/* not needed, do nothing */
		return 0;

	case CODEC_G_VFE:
	case CODEC_S_VFE:
		return 0;

	case CODEC_S_MMAP:
		/* not available, give an error */
		return -ENXIO;

	default:
		return -EINVAL;
	}

	return size;
}