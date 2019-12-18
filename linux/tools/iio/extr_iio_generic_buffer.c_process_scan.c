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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct iio_channel_info {int bytes; int /*<<< orphan*/  location; } ;

/* Variables and functions */
 int /*<<< orphan*/  print1byte (int /*<<< orphan*/ ,struct iio_channel_info*) ; 
 int /*<<< orphan*/  print2byte (int /*<<< orphan*/ ,struct iio_channel_info*) ; 
 int /*<<< orphan*/  print4byte (int /*<<< orphan*/ ,struct iio_channel_info*) ; 
 int /*<<< orphan*/  print8byte (int /*<<< orphan*/ ,struct iio_channel_info*) ; 
 int /*<<< orphan*/  printf (char*) ; 

void process_scan(char *data,
		  struct iio_channel_info *channels,
		  int num_channels)
{
	int k;

	for (k = 0; k < num_channels; k++)
		switch (channels[k].bytes) {
			/* only a few cases implemented so far */
		case 1:
			print1byte(*(uint8_t *)(data + channels[k].location),
				   &channels[k]);
			break;
		case 2:
			print2byte(*(uint16_t *)(data + channels[k].location),
				   &channels[k]);
			break;
		case 4:
			print4byte(*(uint32_t *)(data + channels[k].location),
				   &channels[k]);
			break;
		case 8:
			print8byte(*(uint64_t *)(data + channels[k].location),
				   &channels[k]);
			break;
		default:
			break;
		}
	printf("\n");
}