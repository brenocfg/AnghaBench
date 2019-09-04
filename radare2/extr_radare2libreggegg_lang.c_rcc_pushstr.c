#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dstvar; int /*<<< orphan*/  line; int /*<<< orphan*/  file; int /*<<< orphan*/  callname; } ;
struct TYPE_9__ {TYPE_1__ lang; TYPE_2__* remit; } ;
struct TYPE_8__ {int size; int /*<<< orphan*/  (* set_string ) (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ;int /*<<< orphan*/  (* comment ) (TYPE_3__*,char*,char*,char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ REggEmit ;
typedef  TYPE_3__ REgg ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int r_hex_pair2bin (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void rcc_pushstr(REgg *egg, char *str, int filter) {
	int dotrim;
	int i, j, len, ch;
	REggEmit *e = egg->remit;

	e->comment (egg, "encode %s string (%s) (%s)",
		filter? "filtered": "unfiltered", str, egg->lang.callname);

// fixed by izhuer
	if (filter) {
		for (i = 0; str[i]; i++) {
			dotrim = 0;
			if (str[i] == '\\') {
				switch (str[i + 1]) {
				case 't':
					str[i] = '\t';
					dotrim = 1;
					break;
				case 'n':
					str[i] = '\n';
					dotrim = 1;
					break;
				case 'e':
					str[i] = '\x1b';
					dotrim = 1;
					break;
				case 'x':
					ch = r_hex_pair2bin (str + i + 2);
					if (ch == -1) {
						eprintf ("%s:%d Error string format\n",
							egg->lang.file, egg->lang.line);
					}
					str[i] = (char) ch;
					dotrim = 3;
					break;
				default:
					break;
				}
				if (dotrim) {
					memmove (str + i + 1, str + i + dotrim + 1,
						strlen (str + i + dotrim + 1) + 1);
				}
				// DO NOT forget the '\x00' terminate char
			}
		}
	}

	len = strlen (str);
	j = (len - len % e->size) + e->size;
	e->set_string (egg, egg->lang.dstvar, str, j);
	R_FREE (egg->lang.dstvar);
}