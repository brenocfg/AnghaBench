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
typedef  int u32 ;
typedef  int u16 ;
struct zoran {int dummy; } ;
struct videocodec {TYPE_1__* master_data; } ;
typedef  int __u32 ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int post_office_read (struct zoran*,int,int) ; 
 scalar_t__ post_office_wait (struct zoran*) ; 

__attribute__((used)) static u32
zr36016_read (struct videocodec *codec,
	      u16                reg)
{
	struct zoran *zr = (struct zoran *) codec->master_data->data;
	__u32 data;

	if (post_office_wait(zr)) {
		return -1;
	}

	data = post_office_read(zr, 2, reg & 0x03) & 0xff;	// read
	return data;
}