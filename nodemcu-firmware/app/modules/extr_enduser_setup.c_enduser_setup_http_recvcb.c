#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tcp_pcb {int dummy; } ;
struct pbuf {scalar_t__ tot_len; } ;
struct TYPE_6__ {struct tcp_pcb* conn; struct TYPE_6__* next; } ;
typedef  TYPE_1__ scan_listener_t ;
typedef  scalar_t__ err_t ;
struct TYPE_7__ {scalar_t__ connecting; TYPE_1__* scan_listeners; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  ENDUSER_SETUP_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENDUSER_SETUP_ERR_NONFATAL ; 
 int /*<<< orphan*/  ENDUSER_SETUP_ERR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ENDUSER_SETUP_ERR_UNKOWN_ERROR ; 
 scalar_t__ ERR_ABRT ; 
 scalar_t__ ERR_MEM ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  LITLEN (int /*<<< orphan*/ ) ; 
 char* calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  deferred_close (struct tcp_pcb*) ; 
 int /*<<< orphan*/  enduser_setup_handle_OPTIONS (struct tcp_pcb*,char*,unsigned int) ; 
 int /*<<< orphan*/  enduser_setup_handle_POST (struct tcp_pcb*,char*,unsigned int) ; 
 int enduser_setup_http_handle_credentials (char*,unsigned int) ; 
 int /*<<< orphan*/  enduser_setup_http_serve_header (struct tcp_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ enduser_setup_http_serve_html (struct tcp_pcb*) ; 
 int /*<<< orphan*/  enduser_setup_serve_status (struct tcp_pcb*) ; 
 int /*<<< orphan*/  enduser_setup_serve_status_as_json (struct tcp_pcb*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_scan_listeners () ; 
 int /*<<< orphan*/  http_header_204 ; 
 int /*<<< orphan*/  http_header_302 ; 
 int /*<<< orphan*/  http_header_400 ; 
 int /*<<< orphan*/  http_header_404 ; 
 int /*<<< orphan*/  http_header_405 ; 
 int /*<<< orphan*/  http_header_500 ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  on_scan_done ; 
 unsigned int pbuf_copy_partial (struct pbuf*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  remove_scan_listener (TYPE_1__*) ; 
 TYPE_3__* state ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  tcp_abort (struct tcp_pcb*) ; 
 int /*<<< orphan*/  tcp_arg (struct tcp_pcb*,TYPE_1__*) ; 
 int /*<<< orphan*/  tcp_recved (struct tcp_pcb*,scalar_t__) ; 
 int /*<<< orphan*/  wifi_station_scan (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static err_t enduser_setup_http_recvcb(void *arg, struct tcp_pcb *http_client, struct pbuf *p, err_t err)
{
  ENDUSER_SETUP_DEBUG("enduser_setup_http_recvcb");

  if (!state || err != ERR_OK)
  {
    if (!state)
      ENDUSER_SETUP_DEBUG("ignoring received data while stopped");
    tcp_abort (http_client);
    return ERR_ABRT;
  }

  if (!p) /* remote side closed, close our end too */
  {
    ENDUSER_SETUP_DEBUG("connection closed");
    scan_listener_t *l = arg; /* if it's waiting for scan, we have a ptr here */
    if (l)
      remove_scan_listener (l);

    deferred_close (http_client);
    return ERR_OK;
  }

  char *data = calloc (1, p->tot_len + 1);
  if (!data)
    return ERR_MEM;

  unsigned data_len = pbuf_copy_partial (p, data, p->tot_len, 0);
  tcp_recved (http_client, p->tot_len);
  pbuf_free (p);

  err_t ret = ERR_OK;

#if ENDUSER_SETUP_DEBUG_SHOW_HTTP_REQUEST
  ENDUSER_SETUP_DEBUG(data);
#endif

  if (strncmp(data, "GET ", 4) == 0)
  {
    if (strncmp(data + 4, "/ ", 2) == 0 || strncmp(data + 4, "/?", 2) == 0)
    {
      if (enduser_setup_http_serve_html(http_client) != 0)
      {
        ENDUSER_SETUP_ERROR("http_recvcb failed. Unable to send HTML.", ENDUSER_SETUP_ERR_UNKOWN_ERROR, ENDUSER_SETUP_ERR_NONFATAL);
      }
      else
      {
        goto free_out; /* streaming now in progress */
      }
    }
    else if (strncmp(data + 4, "/aplist", 7) == 0)
    {
      /* Don't do an AP Scan while station is trying to connect to Wi-Fi */
      if (state->connecting == 0)
      {
        scan_listener_t *l = malloc (sizeof (scan_listener_t));
        if (!l)
        {
          ENDUSER_SETUP_ERROR("out of memory", ENDUSER_SETUP_ERR_OUT_OF_MEMORY, ENDUSER_SETUP_ERR_NONFATAL);
        }

        bool already = (state->scan_listeners != NULL);

        tcp_arg (http_client, l);
        /* TODO: check if also need a tcp_err() cb, or if recv() is enough */
        l->conn = http_client;
        l->next = state->scan_listeners;
        state->scan_listeners = l;

        if (!already)
        {
          if (!wifi_station_scan(NULL, on_scan_done))
          {
            enduser_setup_http_serve_header(http_client, http_header_500, LITLEN(http_header_500));
            deferred_close (l->conn);
            l->conn = 0;
            free_scan_listeners();
          }
        }
        goto free_out; /* request queued */
      }
      else
      {
        /* Return No Content status to the caller */
        enduser_setup_http_serve_header(http_client, http_header_204, LITLEN(http_header_204));
      }
    }
    else if (strncmp(data + 4, "/status.json", 12) == 0)
    {
    enduser_setup_serve_status_as_json(http_client);
    }
    else if (strncmp(data + 4, "/status", 7) == 0)
    {
      enduser_setup_serve_status(http_client);
    }

    else if (strncmp(data + 4, "/update?", 8) == 0)
    {
      switch (enduser_setup_http_handle_credentials(data, data_len))
      {
        case 0:
          enduser_setup_http_serve_header(http_client, http_header_302, LITLEN(http_header_302));
          break;
        case 1:
          enduser_setup_http_serve_header(http_client, http_header_400, LITLEN(http_header_400));
          break;
        default:
          ENDUSER_SETUP_ERROR("http_recvcb failed. Failed to handle wifi credentials.", ENDUSER_SETUP_ERR_UNKOWN_ERROR, ENDUSER_SETUP_ERR_NONFATAL);
          break;
      }
    }
    else if (strncmp(data + 4, "/generate_204", 13) == 0)
    {
      /* Convince Android devices that they have internet access to avoid pesky dialogues. */
      enduser_setup_http_serve_header(http_client, http_header_204, LITLEN(http_header_204));
    }
    else
    {
      ENDUSER_SETUP_DEBUG("serving 404");
      enduser_setup_http_serve_header(http_client, http_header_404, LITLEN(http_header_404));
    }
  }
  else if (strncmp(data, "OPTIONS ", 8) == 0)
  {
     enduser_setup_handle_OPTIONS(http_client, data, data_len);
  }
  else if (strncmp(data, "POST ", 5) == 0)
  {
    enduser_setup_handle_POST(http_client, data, data_len);
  }
  else /* not GET or OPTIONS */
  {
    enduser_setup_http_serve_header(http_client, http_header_405, LITLEN(http_header_405));
  }

  deferred_close (http_client);

free_out:
  free (data);
  return ret;
}