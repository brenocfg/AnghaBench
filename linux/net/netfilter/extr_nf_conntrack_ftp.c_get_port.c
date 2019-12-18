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
typedef  int u_int16_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int get_port(const char *data, int start, size_t dlen, char delim,
		    __be16 *port)
{
	u_int16_t tmp_port = 0;
	int i;

	for (i = start; i < dlen; i++) {
		/* Finished? */
		if (data[i] == delim) {
			if (tmp_port == 0)
				break;
			*port = htons(tmp_port);
			pr_debug("get_port: return %d\n", tmp_port);
			return i + 1;
		}
		else if (data[i] >= '0' && data[i] <= '9')
			tmp_port = tmp_port*10 + data[i] - '0';
		else { /* Some other crap */
			pr_debug("get_port: invalid char.\n");
			break;
		}
	}
	return 0;
}