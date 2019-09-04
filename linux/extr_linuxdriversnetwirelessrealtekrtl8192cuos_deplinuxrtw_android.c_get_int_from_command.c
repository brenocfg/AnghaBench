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

/* Variables and functions */
 int rtw_atoi (char*) ; 
 int strlen (char*) ; 

int get_int_from_command( char* pcmd )
{
	int i = 0;

	for( i = 0; i < strlen( pcmd ); i++ )
	{
		if ( pcmd[ i ] == '=' )
		{
			//	Skip the '=' and space characters.
			i += 2;
			break;
		}
	}
	return ( rtw_atoi( pcmd + i ) );
}