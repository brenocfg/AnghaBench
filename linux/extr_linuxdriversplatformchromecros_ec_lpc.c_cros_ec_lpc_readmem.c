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
struct cros_ec_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ EC_LPC_ADDR_MEMMAP ; 
 unsigned int EC_MEMMAP_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  cros_ec_lpc_read_bytes (scalar_t__,int,char*) ; 

__attribute__((used)) static int cros_ec_lpc_readmem(struct cros_ec_device *ec, unsigned int offset,
			       unsigned int bytes, void *dest)
{
	int i = offset;
	char *s = dest;
	int cnt = 0;

	if (offset >= EC_MEMMAP_SIZE - bytes)
		return -EINVAL;

	/* fixed length */
	if (bytes) {
		cros_ec_lpc_read_bytes(EC_LPC_ADDR_MEMMAP + offset, bytes, s);
		return bytes;
	}

	/* string */
	for (; i < EC_MEMMAP_SIZE; i++, s++) {
		cros_ec_lpc_read_bytes(EC_LPC_ADDR_MEMMAP + i, 1, s);
		cnt++;
		if (!*s)
			break;
	}

	return cnt;
}