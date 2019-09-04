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
 int LSAPI_Write (char const*,size_t) ; 
 scalar_t__ lsapi_mode ; 
 int /*<<< orphan*/  php_handle_aborted_connection () ; 
 int write (int,char const*,int) ; 

__attribute__((used)) static size_t sapi_lsapi_ub_write(const char *str, size_t str_length)
{
    int ret;
    int remain;
    if ( lsapi_mode ) {
        ret  = LSAPI_Write( str, str_length );
        if ( ret < str_length ) {
            php_handle_aborted_connection();
            return str_length - ret;
        }
    } else {
        remain = str_length;
        while( remain > 0 ) {
            ret = write( 1, str, remain );
            if ( ret <= 0 ) {
                php_handle_aborted_connection();
                return str_length - remain;
            }
            str += ret;
            remain -= ret;
        }
    }
    return str_length;
}