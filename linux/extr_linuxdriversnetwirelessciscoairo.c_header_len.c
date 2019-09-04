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
typedef  int u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int header_len(__le16 ctl)
{
	u16 fc = le16_to_cpu(ctl);
	switch (fc & 0xc) {
	case 4:
		if ((fc & 0xe0) == 0xc0)
			return 10;	/* one-address control packet */
		return 16;	/* two-address control packet */
	case 8:
		if ((fc & 0x300) == 0x300)
			return 30;	/* WDS packet */
	}
	return 24;
}