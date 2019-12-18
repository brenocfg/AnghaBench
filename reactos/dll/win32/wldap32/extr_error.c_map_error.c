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
typedef  int ULONG ;

/* Variables and functions */
#define  LDAP_AUTH_UNKNOWN 143 
#define  LDAP_CLIENT_LOOP 142 
#define  LDAP_CONNECT_ERROR 141 
#define  LDAP_CONTROL_NOT_FOUND 140 
#define  LDAP_DECODING_ERROR 139 
#define  LDAP_FILTER_ERROR 138 
#define  LDAP_LOCAL_ERROR 137 
#define  LDAP_MORE_RESULTS_TO_RETURN 136 
#define  LDAP_NOT_SUPPORTED 135 
#define  LDAP_NO_MEMORY 134 
#define  LDAP_NO_RESULTS_RETURNED 133 
#define  LDAP_PARAM_ERROR 132 
#define  LDAP_REFERRAL_LIMIT_EXCEEDED 131 
#define  LDAP_SERVER_DOWN 130 
#define  LDAP_TIMEOUT 129 
#define  LDAP_USER_CANCELLED 128 
 int WLDAP32_LDAP_AUTH_UNKNOWN ; 
 int WLDAP32_LDAP_CLIENT_LOOP ; 
 int WLDAP32_LDAP_CONNECT_ERROR ; 
 int WLDAP32_LDAP_CONTROL_NOT_FOUND ; 
 int WLDAP32_LDAP_DECODING_ERROR ; 
 int WLDAP32_LDAP_FILTER_ERROR ; 
 int WLDAP32_LDAP_LOCAL_ERROR ; 
 int WLDAP32_LDAP_MORE_RESULTS_TO_RETURN ; 
 int WLDAP32_LDAP_NOT_SUPPORTED ; 
 int WLDAP32_LDAP_NO_MEMORY ; 
 int WLDAP32_LDAP_NO_RESULTS_RETURNED ; 
 int WLDAP32_LDAP_PARAM_ERROR ; 
 int WLDAP32_LDAP_REFERRAL_LIMIT_EXCEEDED ; 
 int WLDAP32_LDAP_SERVER_DOWN ; 
 int WLDAP32_LDAP_TIMEOUT ; 
 int WLDAP32_LDAP_USER_CANCELLED ; 

ULONG map_error( int error )
{
    switch (error)
    {
#ifdef HAVE_LDAP_H
    case LDAP_SERVER_DOWN:              return WLDAP32_LDAP_SERVER_DOWN;
    case LDAP_LOCAL_ERROR:              return WLDAP32_LDAP_LOCAL_ERROR;
    case LDAP_DECODING_ERROR:           return WLDAP32_LDAP_DECODING_ERROR;
    case LDAP_TIMEOUT:                  return WLDAP32_LDAP_TIMEOUT;
    case LDAP_AUTH_UNKNOWN:             return WLDAP32_LDAP_AUTH_UNKNOWN;
    case LDAP_FILTER_ERROR:             return WLDAP32_LDAP_FILTER_ERROR;
    case LDAP_USER_CANCELLED:           return WLDAP32_LDAP_USER_CANCELLED;
    case LDAP_PARAM_ERROR:              return WLDAP32_LDAP_PARAM_ERROR;
    case LDAP_NO_MEMORY:                return WLDAP32_LDAP_NO_MEMORY;
    case LDAP_CONNECT_ERROR:            return WLDAP32_LDAP_CONNECT_ERROR;
    case LDAP_NOT_SUPPORTED:            return WLDAP32_LDAP_NOT_SUPPORTED;
    case LDAP_CONTROL_NOT_FOUND:        return WLDAP32_LDAP_CONTROL_NOT_FOUND;
    case LDAP_NO_RESULTS_RETURNED:      return WLDAP32_LDAP_NO_RESULTS_RETURNED;
    case LDAP_MORE_RESULTS_TO_RETURN:   return WLDAP32_LDAP_MORE_RESULTS_TO_RETURN;
    case LDAP_CLIENT_LOOP:              return WLDAP32_LDAP_CLIENT_LOOP;
    case LDAP_REFERRAL_LIMIT_EXCEEDED:  return WLDAP32_LDAP_REFERRAL_LIMIT_EXCEEDED;
#endif
    default: return error;
    }
}