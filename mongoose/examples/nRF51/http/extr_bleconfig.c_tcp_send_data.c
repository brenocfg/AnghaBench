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
typedef  char uint8_t ;
typedef  int uint32_t ;
struct tcp_pcb {int dummy; } ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_LOG (char*,scalar_t__) ; 
 scalar_t__ ERR_OK ; 
 int TCP_DATA_SIZE ; 
 scalar_t__ TCP_STATE_DATA_TX_IN_PROGRESS ; 
 scalar_t__ m_tcp_state ; 
 int /*<<< orphan*/  tcp_sent (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_write (struct tcp_pcb*,char*,int,int) ; 
 int /*<<< orphan*/  tcp_write_complete ; 

__attribute__((used)) static void tcp_send_data(struct tcp_pcb * p_pcb, uint32_t sequence_number)
{
  err_t  err = ERR_OK;

  if (m_tcp_state != TCP_STATE_DATA_TX_IN_PROGRESS)
  {
    //Register callback to get notification of data reception is complete.
    tcp_sent(p_pcb, tcp_write_complete);
    uint8_t tcp_data[TCP_DATA_SIZE];

    tcp_data[0] = (uint8_t )((sequence_number >> 24) & 0x000000FF);
    tcp_data[1] = (uint8_t )((sequence_number >> 16) & 0x000000FF);
    tcp_data[2] = (uint8_t )((sequence_number >> 8)  & 0x000000FF);
    tcp_data[3] = (uint8_t )(sequence_number         & 0x000000FF);

    tcp_data[4] = 'P';
    tcp_data[5] = 'o';
    tcp_data[6] = 'n';
    tcp_data[7] = 'g';

    //Enqueue data for transmission.
    err = tcp_write(p_pcb, tcp_data, TCP_DATA_SIZE, 1);

    if (err != ERR_OK)
    {
      APPL_LOG ("[APPL]: Failed to send TCP packet, reason %d\r\n", err);
    }
    else
    {
      m_tcp_state = TCP_STATE_DATA_TX_IN_PROGRESS;
    }
  }
  else
  {
    //Wait for tx to be complete.
  }
}