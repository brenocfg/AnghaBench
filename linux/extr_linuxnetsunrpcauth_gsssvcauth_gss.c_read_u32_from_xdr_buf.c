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
typedef  int /*<<< orphan*/  u32 ;
struct xdr_buf {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int read_bytes_from_xdr_buf (struct xdr_buf*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int
read_u32_from_xdr_buf(struct xdr_buf *buf, int base, u32 *obj)
{
	__be32  raw;
	int     status;

	status = read_bytes_from_xdr_buf(buf, base, &raw, sizeof(*obj));
	if (status)
		return status;
	*obj = ntohl(raw);
	return 0;
}