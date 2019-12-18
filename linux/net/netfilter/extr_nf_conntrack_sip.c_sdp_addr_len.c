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
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  sdp_parse_addr (struct nf_conn const*,char const*,char const**,union nf_inet_addr*,char const*) ; 

__attribute__((used)) static int sdp_addr_len(const struct nf_conn *ct, const char *dptr,
			const char *limit, int *shift)
{
	union nf_inet_addr addr;
	const char *aux = dptr;

	if (!sdp_parse_addr(ct, dptr, &dptr, &addr, limit)) {
		pr_debug("ip: %s parse failed.!\n", dptr);
		return 0;
	}

	return dptr - aux;
}