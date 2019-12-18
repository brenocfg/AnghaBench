#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* values; size_t colorsPerLed; size_t size; } ;
typedef  TYPE_1__ ws2812_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ws2812_write_data (char const*,size_t,char const*,size_t) ; 

__attribute__((used)) static int ws2812_write(ws2812_buffer* buffer) {
  size_t length1, length2;
  const char *buffer1, *buffer2;

  buffer1 = 0;
  length1 = 0;

  buffer1 = buffer->values;
  length1 = buffer->colorsPerLed*buffer->size;

  buffer2 = 0;
  length2 = 0;

  // Send the buffers
  ws2812_write_data(buffer1, length1, buffer2, length2);

  return 0;
}