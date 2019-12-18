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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  uchar ;
typedef  int /*<<< orphan*/  sha1_context ;

/* Variables and functions */
 int /*<<< orphan*/  sha1_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha1_starts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha1_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sha1_csum( uchar *buf, uint buflen, uchar digest[20] )
{
    sha1_context ctx;

    sha1_starts( &ctx );
    sha1_update( &ctx, buf, buflen );
    sha1_finish( &ctx, digest );
}