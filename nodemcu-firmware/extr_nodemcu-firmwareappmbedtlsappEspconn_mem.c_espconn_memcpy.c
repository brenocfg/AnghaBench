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

void *espconn_memcpy(void *dst, const void *src, size_t size, char *file, int line)
{
	char *psrc = NULL;
	char *pdst = NULL;

	if(NULL == dst || NULL == src)
	{
		return NULL;
	}
	//os_printf("%s %d %p %p %d\n",file, line, dst, src, size);
	if((src < dst) && (char *)src + size > (char *)dst)
	{
		psrc = (char *)src + size - 1;
		pdst = (char *)dst + size - 1;
		while(size--)
		{
			*pdst-- = *psrc--;
		}
	}
	else
	{
		psrc = (char *)src;
		pdst = (char *)dst;
		while(size--)
		{
			*pdst++ = *psrc++;
		}
	}

	return dst;

}