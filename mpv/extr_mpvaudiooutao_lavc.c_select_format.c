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
struct ao {int format; } ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  AF_FORMAT_COUNT ; 
 int /*<<< orphan*/  af_get_best_sample_formats (int,int*) ; 
 scalar_t__ supports_format (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void select_format(struct ao *ao, const AVCodec *codec)
{
    int formats[AF_FORMAT_COUNT + 1];
    af_get_best_sample_formats(ao->format, formats);

    for (int n = 0; formats[n]; n++) {
        if (supports_format(codec, formats[n])) {
            ao->format = formats[n];
            break;
        }
    }
}