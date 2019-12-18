#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct TYPE_4__ {TYPE_1__ tcp; } ;
struct nf_conntrack_man {TYPE_2__ u; } ;

/* Variables and functions */
 int get_port (char const*,int,size_t,char,int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (char) ; 

__attribute__((used)) static int try_epsv_response(const char *data, size_t dlen,
			     struct nf_conntrack_man *cmd, char term,
			     unsigned int *offset)
{
	char delim;

	/* Three delimiters. */
	if (dlen <= 3) return 0;
	delim = data[0];
	if (isdigit(delim) || delim < 33 || delim > 126 ||
	    data[1] != delim || data[2] != delim)
		return 0;

	return get_port(data, 3, dlen, delim, &cmd->u.tcp.port);
}