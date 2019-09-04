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
#define  MQTT_MSG_TYPE_PUBACK 135 
#define  MQTT_MSG_TYPE_PUBCOMP 134 
#define  MQTT_MSG_TYPE_PUBLISH 133 
#define  MQTT_MSG_TYPE_PUBREC 132 
#define  MQTT_MSG_TYPE_PUBREL 131 
#define  MQTT_MSG_TYPE_SUBACK 130 
#define  MQTT_MSG_TYPE_SUBSCRIBE 129 
#define  MQTT_MSG_TYPE_UNSUBACK 128 
 int /*<<< orphan*/  mqtt_get_qos (int*) ; 
 int mqtt_get_type (int*) ; 

uint16_t mqtt_get_id(uint8_t* buffer, uint16_t buffer_length)
{
  if(buffer_length < 1)
    return 0;

  switch(mqtt_get_type(buffer))
  {
    case MQTT_MSG_TYPE_PUBLISH:
    {
      int i;
      int topiclen;

      if(mqtt_get_qos(buffer) <= 0)
        return 0;

      for(i = 1; i < buffer_length; ++i)
      {
        if((buffer[i] & 0x80) == 0)
        {
          ++i;
          break;
        }
      }

      if(i + 2 > buffer_length)
        return 0;
      topiclen = buffer[i++] << 8;
      topiclen |= buffer[i++];

      if(i + topiclen > buffer_length)
        return 0;
      i += topiclen;

      if(i + 2 > buffer_length)
        return 0;

      return (buffer[i] << 8) | buffer[i + 1];
    }
    case MQTT_MSG_TYPE_PUBACK:
    case MQTT_MSG_TYPE_PUBREC:
    case MQTT_MSG_TYPE_PUBREL:
    case MQTT_MSG_TYPE_PUBCOMP:
    case MQTT_MSG_TYPE_SUBACK:
    case MQTT_MSG_TYPE_UNSUBACK:
    case MQTT_MSG_TYPE_SUBSCRIBE:
    {
      // This requires the remaining length to be encoded in 1 byte,
      // which it should be.
      if(buffer_length >= 4 && (buffer[1] & 0x80) == 0)
        return (buffer[2] << 8) | buffer[3];
      else
        return 0;
    }

    default:
      return 0;
  }
}