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
typedef  char uint32 ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  des_init () ; 
 int /*<<< orphan*/  des_initialised ; 
 int do_des (char,char,char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char pg_hton32 (char) ; 
 char pg_ntoh32 (char) ; 
 int /*<<< orphan*/  setup_salt (long) ; 

__attribute__((used)) static int
des_cipher(const char *in, char *out, long salt, int count)
{
	uint32		buffer[2];
	uint32		l_out,
				r_out,
				rawl,
				rawr;
	int			retval;

	if (!des_initialised)
		des_init();

	setup_salt(salt);

	/* copy data to avoid assuming input is word-aligned */
	memcpy(buffer, in, sizeof(buffer));

	rawl = pg_ntoh32(buffer[0]);
	rawr = pg_ntoh32(buffer[1]);

	retval = do_des(rawl, rawr, &l_out, &r_out, count);
	if (retval)
		return retval;

	buffer[0] = pg_hton32(l_out);
	buffer[1] = pg_hton32(r_out);

	/* copy data to avoid assuming output is word-aligned */
	memcpy(out, buffer, sizeof(buffer));

	return retval;
}