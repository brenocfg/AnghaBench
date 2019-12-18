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
typedef  int ut8 ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  memcmp (int*,char*,int) ; 
 int r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool check_buffer(RBuffer *b) {
	ut8 buf[8];
	if (r_buf_read_at (b, 0, buf, sizeof (buf)) != sizeof (buf)) {
		return false;
	}
	if (r_buf_size (b) >= 32 && !memcmp (buf, "MENUET0", 7)) {
		switch (buf[7]) {
		case '0':
		case '1':
		case '2':
			return true;
		}
		eprintf ("Unsupported MENUET version header\n");
	}
	return false;
}