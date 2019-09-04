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
struct AVCodecContext {int dummy; } ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int AV_PIX_FMT_YUV420P ; 

enum AVPixelFormat get_hwaccel_format(struct AVCodecContext *s,
		const enum AVPixelFormat * fmt)
{
	(void)s;
	(void)fmt;

	// for now force output to common denominator
	return AV_PIX_FMT_YUV420P;
}