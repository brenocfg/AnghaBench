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
typedef  size_t yy_state_type ;
typedef  size_t YY_CHAR ;

/* Variables and functions */
 scalar_t__* yy_accept ; 
 size_t* yy_base ; 
 char* yy_c_buf_p ; 
 size_t* yy_chk ; 
 scalar_t__* yy_def ; 
 char* yy_last_accepting_cpos ; 
 size_t yy_last_accepting_state ; 
 size_t* yy_meta ; 
 size_t* yy_nxt ; 

__attribute__((used)) static yy_state_type yy_try_NUL_trans  (yy_state_type yy_current_state )
{
	register int yy_is_jam;
    	register char *yy_cp = (yy_c_buf_p);

	register YY_CHAR yy_c = 1;
	if ( yy_accept[yy_current_state] )
		{
		(yy_last_accepting_state) = yy_current_state;
		(yy_last_accepting_cpos) = yy_cp;
		}
	while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
		{
		yy_current_state = (int) yy_def[yy_current_state];
		if ( yy_current_state >= 481 )
			yy_c = yy_meta[(unsigned int) yy_c];
		}
	yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
	yy_is_jam = (yy_current_state == 480);

	return yy_is_jam ? 0 : yy_current_state;
}