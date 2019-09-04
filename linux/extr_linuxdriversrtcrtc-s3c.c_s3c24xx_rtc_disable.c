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
struct s3c_rtc {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ S3C2410_RTCCON ; 
 unsigned int S3C2410_RTCCON_RTCEN ; 
 scalar_t__ S3C2410_TICNT ; 
 unsigned int S3C2410_TICNT_ENABLE ; 
 unsigned int readb (scalar_t__) ; 
 unsigned int readw (scalar_t__) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static void s3c24xx_rtc_disable(struct s3c_rtc *info)
{
	unsigned int con;

	con = readw(info->base + S3C2410_RTCCON);
	con &= ~S3C2410_RTCCON_RTCEN;
	writew(con, info->base + S3C2410_RTCCON);

	con = readb(info->base + S3C2410_TICNT);
	con &= ~S3C2410_TICNT_ENABLE;
	writeb(con, info->base + S3C2410_TICNT);
}