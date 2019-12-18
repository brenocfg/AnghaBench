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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ LSAPI_ReadReqBody (char*,unsigned long long) ; 
 scalar_t__ lsapi_mode ; 

__attribute__((used)) static size_t sapi_lsapi_read_post(char *buffer, size_t count_bytes)
{
    if ( lsapi_mode ) {
        ssize_t rv = LSAPI_ReadReqBody(buffer, (unsigned long long)count_bytes);
        return (rv >= 0) ? (size_t)rv : 0;
    } else {
        return 0;
    }
}