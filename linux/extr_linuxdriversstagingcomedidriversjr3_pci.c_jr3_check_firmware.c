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
typedef  int /*<<< orphan*/  u8 ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ read_idm_word (int /*<<< orphan*/  const*,size_t,int*,unsigned int*) ; 

__attribute__((used)) static int jr3_check_firmware(struct comedi_device *dev,
			      const u8 *data, size_t size)
{
	int more = 1;
	int pos = 0;

	/*
	 * IDM file format is:
	 *   { count, address, data <count> } *
	 *   ffff
	 */
	while (more) {
		unsigned int count = 0;
		unsigned int addr = 0;

		more = more && read_idm_word(data, size, &pos, &count);
		if (more && count == 0xffff)
			return 0;

		more = more && read_idm_word(data, size, &pos, &addr);
		while (more && count > 0) {
			unsigned int dummy = 0;

			more = more && read_idm_word(data, size, &pos, &dummy);
			count--;
		}
	}

	return -ENODATA;
}