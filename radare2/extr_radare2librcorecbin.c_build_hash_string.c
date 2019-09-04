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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut32 ;
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 scalar_t__ IS_MODE_JSON (int) ; 
 scalar_t__ IS_MODE_SIMPLE (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_hash_to_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* r_str_append (char*,char*) ; 
 char* r_str_newf (char*,char*,...) ; 
 int /*<<< orphan*/  r_str_trim_head_tail (char*) ; 

__attribute__((used)) static char *build_hash_string(int mode, const char *chksum, ut8 *data, ut32 datalen) {
	char *chkstr = NULL, *aux, *ret = NULL;
	const char *ptr = chksum;
	char tmp[128];
	int i;
	do {
		for (i = 0; *ptr && *ptr != ',' && i < sizeof (tmp) -1; i++) {
			tmp[i] = *ptr++;
		}
		tmp[i] = '\0';
		r_str_trim_head_tail (tmp);
		chkstr = r_hash_to_string (NULL, tmp, data, datalen);
		if (!chkstr) {
			if (*ptr && *ptr == ',') {
				ptr++;
			}
			continue;
		}
		if (IS_MODE_SIMPLE (mode)) {
			aux = r_str_newf ("%s ", chkstr);
		} else if (IS_MODE_JSON (mode)) {
			aux = r_str_newf ("\"%s\":\"%s\",", tmp, chkstr);
		} else {
			aux = r_str_newf ("%s=%s ", tmp, chkstr);
		}
		ret = r_str_append (ret, aux);
		free (chkstr);
		free (aux);
		if (*ptr && *ptr == ',') {
			ptr++;
		}
	} while (*ptr);

	return ret;
}