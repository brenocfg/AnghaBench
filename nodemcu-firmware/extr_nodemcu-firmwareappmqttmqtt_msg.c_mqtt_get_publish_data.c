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
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 scalar_t__ mqtt_get_qos (int*) ; 

const char* mqtt_get_publish_data(uint8_t* buffer, uint16_t* buffer_length)
{
  int i;
  int totlen = 0;
  int topiclen;

  for(i = 1; i < *buffer_length; ++i)
  {
    totlen += (buffer[i] & 0x7f) << (7 * (i - 1));
    if((buffer[i] & 0x80) == 0)
    {
      ++i;
      break;
    }
  }
  totlen += i;

  if(i + 2 > *buffer_length)
    return NULL;
  topiclen = buffer[i++] << 8;
  topiclen |= buffer[i++];

  if(i + topiclen > *buffer_length){
	*buffer_length = 0;
    return NULL;
  }
  i += topiclen;

  if(mqtt_get_qos(buffer) > 0)
  {
    if(i + 2 > *buffer_length)
      return NULL;
    i += 2;
  }

  if(totlen < i)
    return NULL;

  if(totlen <= *buffer_length)
    *buffer_length = totlen - i;
  else
    *buffer_length = *buffer_length - i;
  return (const char*)(buffer + i);
}