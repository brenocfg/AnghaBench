#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_llist_position ;
struct TYPE_9__ {int /*<<< orphan*/  headers; } ;
typedef  TYPE_1__ sapi_headers_struct ;
struct TYPE_10__ {scalar_t__ header_len; char* header; } ;
typedef  TYPE_2__ sapi_header_struct ;
struct TYPE_11__ {scalar_t__ send_default_content_type; int /*<<< orphan*/  http_response_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSAPI_AppendRespHeader (char*,int) ; 
 int /*<<< orphan*/  LSAPI_FinalizeRespHeaders () ; 
 int /*<<< orphan*/  LSAPI_SetRespStatus (int /*<<< orphan*/ ) ; 
 int SAPI_HEADER_SENT_SUCCESSFULLY ; 
 int SAPI_LSAPI_MAX_HEADER_LENGTH ; 
 TYPE_7__ SG (TYPE_1__*) ; 
 int /*<<< orphan*/  efree (char*) ; 
 scalar_t__ lsapi_mode ; 
 scalar_t__ mod_lsapi_mode ; 
 char* sapi_get_default_content_type () ; 
 int sapi_lsapi_send_headers_like_cgi (TYPE_1__*) ; 
 int snprintf (char*,int,char*,char*) ; 
 TYPE_2__* zend_llist_get_first_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* zend_llist_get_next_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sapi_lsapi_send_headers(sapi_headers_struct *sapi_headers)
{
    sapi_header_struct  *h;
    zend_llist_position pos;

    if ( mod_lsapi_mode ) {
        /* mod_lsapi mode */
        return sapi_lsapi_send_headers_like_cgi(sapi_headers);
    }

    /* Legacy mode */
    if ( lsapi_mode ) {
        LSAPI_SetRespStatus( SG(sapi_headers).http_response_code );

        h = zend_llist_get_first_ex(&sapi_headers->headers, &pos);
        while (h) {
            if ( h->header_len > 0 ) {
                LSAPI_AppendRespHeader(h->header, h->header_len);
            }
            h = zend_llist_get_next_ex(&sapi_headers->headers, &pos);
        }
        if (SG(sapi_headers).send_default_content_type) {
            char    *hd;
            int     len;
            char    headerBuf[SAPI_LSAPI_MAX_HEADER_LENGTH];

            hd = sapi_get_default_content_type();
            len = snprintf( headerBuf, SAPI_LSAPI_MAX_HEADER_LENGTH - 1,
                            "Content-type: %s", hd );
            efree(hd);

            LSAPI_AppendRespHeader( headerBuf, len );
        }
    }
    LSAPI_FinalizeRespHeaders();
    return SAPI_HEADER_SENT_SUCCESSFULLY;


}