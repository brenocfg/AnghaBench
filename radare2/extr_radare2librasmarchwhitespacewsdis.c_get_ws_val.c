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
typedef  char ut8 ;
typedef  int st32 ;

/* Variables and functions */
 char* get_ws_next_token (char const*,int) ; 

__attribute__((used)) static st32 get_ws_val(const ut8 *buf, int len) {
	ut8 sig;
	int i, ret = 0;
	const ut8 *tok = get_ws_next_token (buf, len);
	sig = (*tok == '\t');
	len -= (tok - buf) + 1;
	for (i = 0; i < 30; i++) { // XXX : conceptually wrong
		tok++;
		tok = get_ws_next_token (tok, len);
		if (!tok || *tok == 10) {
			if (sig) {
				return ret * (-1);
			}
			return ret;
		}
		ret = (ret << 1);
		ret = ret + (*tok == '\t');
		len = len - (tok - buf) - 1;
	}
	return sig? ret * (-1): ret;
}