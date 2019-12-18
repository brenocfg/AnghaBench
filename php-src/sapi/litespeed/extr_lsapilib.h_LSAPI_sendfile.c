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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  LSAPI_sendfile_r (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  g_req ; 

__attribute__((used)) static inline ssize_t LSAPI_sendfile( int fdIn, off_t* off, size_t size )
{
    return LSAPI_sendfile_r(&g_req, fdIn, off, size );
}