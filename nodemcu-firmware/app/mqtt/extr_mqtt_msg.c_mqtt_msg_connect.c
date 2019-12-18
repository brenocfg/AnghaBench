#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct mqtt_connect_variable_header {int lengthLsb; int version; int flags; int keepaliveMsb; int keepaliveLsb; int /*<<< orphan*/  magic; scalar_t__ lengthMsb; } ;
typedef  int /*<<< orphan*/  mqtt_message_t ;
struct TYPE_10__ {scalar_t__ length; } ;
struct TYPE_11__ {scalar_t__ buffer_length; scalar_t__ buffer; TYPE_1__ message; } ;
typedef  TYPE_2__ mqtt_connection_t ;
struct TYPE_12__ {int keepalive; char* client_id; char* will_topic; char* will_message; int will_qos; char* username; char* password; scalar_t__ will_retain; scalar_t__ clean_session; } ;
typedef  TYPE_3__ mqtt_connect_info_t ;

/* Variables and functions */
 int MQTT_CONNECT_FLAG_CLEAN_SESSION ; 
 int MQTT_CONNECT_FLAG_PASSWORD ; 
 int MQTT_CONNECT_FLAG_USERNAME ; 
 int MQTT_CONNECT_FLAG_WILL ; 
 int MQTT_CONNECT_FLAG_WILL_RETAIN ; 
 int /*<<< orphan*/  MQTT_MSG_TYPE_CONNECT ; 
 scalar_t__ append_string (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fail_message (TYPE_2__*) ; 
 int /*<<< orphan*/ * fini_message (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_message (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

mqtt_message_t* mqtt_msg_connect(mqtt_connection_t* connection, mqtt_connect_info_t* info)
{
  struct mqtt_connect_variable_header* variable_header;

  init_message(connection);

  if(connection->message.length + sizeof(*variable_header) > connection->buffer_length)
    return fail_message(connection);
  variable_header = (void*)(connection->buffer + connection->message.length);
  connection->message.length += sizeof(*variable_header);

  variable_header->lengthMsb = 0;
  variable_header->lengthLsb = 4;
  memcpy(variable_header->magic, "MQTT", 4);
  variable_header->version = 4;
  variable_header->flags = 0;
  variable_header->keepaliveMsb = info->keepalive >> 8;
  variable_header->keepaliveLsb = info->keepalive & 0xff;

  if(info->clean_session)
    variable_header->flags |= MQTT_CONNECT_FLAG_CLEAN_SESSION;

  if(info->client_id != NULL && info->client_id[0] != '\0')
  {
    if(append_string(connection, info->client_id, strlen(info->client_id)) < 0)
      return fail_message(connection);
  }
  else
    return fail_message(connection);

  if(info->will_topic != NULL && info->will_topic[0] != '\0')
  {
    if(append_string(connection, info->will_topic, strlen(info->will_topic)) < 0)
      return fail_message(connection);

    if(append_string(connection, info->will_message, strlen(info->will_message)) < 0)
      return fail_message(connection);

    variable_header->flags |= MQTT_CONNECT_FLAG_WILL;
    if(info->will_retain)
      variable_header->flags |= MQTT_CONNECT_FLAG_WILL_RETAIN;
    variable_header->flags |= (info->will_qos & 3) << 3;
  }

  if(info->username != NULL && info->username[0] != '\0')
  {
    if(append_string(connection, info->username, strlen(info->username)) < 0)
      return fail_message(connection);

    variable_header->flags |= MQTT_CONNECT_FLAG_USERNAME;
  }

  if(info->password != NULL && info->password[0] != '\0')
  {
    if(append_string(connection, info->password, strlen(info->password)) < 0)
      return fail_message(connection);

    variable_header->flags |= MQTT_CONNECT_FLAG_PASSWORD;
  }

  return fini_message(connection, MQTT_MSG_TYPE_CONNECT, 0, 0, 0);
}