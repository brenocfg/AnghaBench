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
typedef  scalar_t__ u8 ;
typedef  size_t u16 ;
typedef  int /*<<< orphan*/  type ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static inline u16 eir_append_data(u8 *eir, u16 eir_len, u8 type,
				  u8 *data, u8 data_len)
{
	eir[eir_len++] = sizeof(type) + data_len;
	eir[eir_len++] = type;
	memcpy(&eir[eir_len], data, data_len);
	eir_len += data_len;

	return eir_len;
}