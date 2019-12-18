#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {int length; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {int msg_type; int publish_qos; struct TYPE_9__* next; int /*<<< orphan*/  msg_id; TYPE_1__ msg; } ;
typedef  TYPE_2__ msg_queue_t ;
struct TYPE_10__ {int length; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ mqtt_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

msg_queue_t *msg_enqueue(msg_queue_t **head, mqtt_message_t *msg, uint16_t msg_id, int msg_type, int publish_qos){
  if(!head){
    return NULL;
  }
  if (!msg || !msg->data || msg->length == 0){
    NODE_DBG("empty message\n");
    return NULL;
  }
  msg_queue_t *node = (msg_queue_t *)calloc(1,sizeof(msg_queue_t));
  if(!node){
    NODE_DBG("not enough memory\n");
    return NULL;
  }

  node->msg.data = (uint8_t *)calloc(1,msg->length);
  if(!node->msg.data){
    NODE_DBG("not enough memory\n");
    free(node);
    return NULL;
  }
  memcpy(node->msg.data, msg->data, msg->length);
  node->msg.length = msg->length;
  node->next = NULL;
  node->msg_id = msg_id;
  node->msg_type = msg_type;
  node->publish_qos = publish_qos;

  msg_queue_t *tail = *head;
  if(tail){
    while(tail->next!=NULL) tail = tail->next;
    tail->next = node;
  } else {
    *head = node;
  }
  return node;
}