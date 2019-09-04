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
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  get_called ; 
 int /*<<< orphan*/ * get_sess_val ; 

__attribute__((used)) static SSL_SESSION *get_session_cb(SSL *ssl, const unsigned char *id, int len,
                                   int *copy)
{
    get_called++;
    *copy = 1;
    return get_sess_val;
}