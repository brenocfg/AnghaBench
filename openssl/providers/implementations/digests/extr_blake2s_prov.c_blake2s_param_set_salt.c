#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ salt; } ;
typedef  TYPE_1__ BLAKE2S_PARAM ;

/* Variables and functions */
 scalar_t__ BLAKE2S_SALTBYTES ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

void blake2s_param_set_salt(BLAKE2S_PARAM *P, const uint8_t *salt, size_t len)
{
    memcpy(P->salt, salt, len);
    memset(P->salt + len, 0, BLAKE2S_SALTBYTES - len);}