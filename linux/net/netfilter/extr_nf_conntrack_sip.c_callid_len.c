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
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int word_len (char const*,char const*) ; 

__attribute__((used)) static int callid_len(const struct nf_conn *ct, const char *dptr,
		      const char *limit, int *shift)
{
	int len, domain_len;

	len = word_len(dptr, limit);
	dptr += len;
	if (!len || dptr == limit || *dptr != '@')
		return len;
	dptr++;
	len++;

	domain_len = word_len(dptr, limit);
	if (!domain_len)
		return 0;
	return len + domain_len;
}