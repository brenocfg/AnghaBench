#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  port; } ;
struct TYPE_6__ {TYPE_2__ tcp; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip; } ;
struct nf_conntrack_man {TYPE_3__ u; TYPE_1__ u3; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int try_number (char const*,size_t,int*,int,char,char) ; 

__attribute__((used)) static int try_rfc959(const char *data, size_t dlen,
		      struct nf_conntrack_man *cmd, char term,
		      unsigned int *offset)
{
	int length;
	u_int32_t array[6];

	length = try_number(data, dlen, array, 6, ',', term);
	if (length == 0)
		return 0;

	cmd->u3.ip = htonl((array[0] << 24) | (array[1] << 16) |
				    (array[2] << 8) | array[3]);
	cmd->u.tcp.port = htons((array[4] << 8) | array[5]);
	return length;
}