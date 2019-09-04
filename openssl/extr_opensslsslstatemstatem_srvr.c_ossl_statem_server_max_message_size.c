#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int hand_state; } ;
struct TYPE_4__ {size_t max_cert_list; TYPE_2__ statem; } ;
typedef  TYPE_1__ SSL ;
typedef  TYPE_2__ OSSL_STATEM ;

/* Variables and functions */
 size_t CCS_MAX_LENGTH ; 
 size_t CLIENT_HELLO_MAX_LENGTH ; 
 size_t CLIENT_KEY_EXCH_MAX_LENGTH ; 
 size_t END_OF_EARLY_DATA_MAX_LENGTH ; 
 size_t FINISHED_MAX_LENGTH ; 
 size_t KEY_UPDATE_MAX_LENGTH ; 
 size_t NEXT_PROTO_MAX_LENGTH ; 
 size_t SSL3_RT_MAX_PLAIN_LENGTH ; 
#define  TLS_ST_SR_CERT 136 
#define  TLS_ST_SR_CERT_VRFY 135 
#define  TLS_ST_SR_CHANGE 134 
#define  TLS_ST_SR_CLNT_HELLO 133 
#define  TLS_ST_SR_END_OF_EARLY_DATA 132 
#define  TLS_ST_SR_FINISHED 131 
#define  TLS_ST_SR_KEY_EXCH 130 
#define  TLS_ST_SR_KEY_UPDATE 129 
#define  TLS_ST_SR_NEXT_PROTO 128 

size_t ossl_statem_server_max_message_size(SSL *s)
{
    OSSL_STATEM *st = &s->statem;

    switch (st->hand_state) {
    default:
        /* Shouldn't happen */
        return 0;

    case TLS_ST_SR_CLNT_HELLO:
        return CLIENT_HELLO_MAX_LENGTH;

    case TLS_ST_SR_END_OF_EARLY_DATA:
        return END_OF_EARLY_DATA_MAX_LENGTH;

    case TLS_ST_SR_CERT:
        return s->max_cert_list;

    case TLS_ST_SR_KEY_EXCH:
        return CLIENT_KEY_EXCH_MAX_LENGTH;

    case TLS_ST_SR_CERT_VRFY:
        return SSL3_RT_MAX_PLAIN_LENGTH;

#ifndef OPENSSL_NO_NEXTPROTONEG
    case TLS_ST_SR_NEXT_PROTO:
        return NEXT_PROTO_MAX_LENGTH;
#endif

    case TLS_ST_SR_CHANGE:
        return CCS_MAX_LENGTH;

    case TLS_ST_SR_FINISHED:
        return FINISHED_MAX_LENGTH;

    case TLS_ST_SR_KEY_UPDATE:
        return KEY_UPDATE_MAX_LENGTH;
    }
}