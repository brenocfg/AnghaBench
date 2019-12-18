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
struct nf_conntrack_man {int dummy; } ;

/* Variables and functions */
 scalar_t__ isdigit (char const) ; 
 int try_rfc959 (char const*,size_t,struct nf_conntrack_man*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int try_rfc1123(const char *data, size_t dlen,
		       struct nf_conntrack_man *cmd, char term,
		       unsigned int *offset)
{
	int i;
	for (i = 0; i < dlen; i++)
		if (isdigit(data[i]))
			break;

	if (i == dlen)
		return 0;

	*offset += i;

	return try_rfc959(data + i, dlen - i, cmd, 0, offset);
}