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
struct snd_ali {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,unsigned int) ; 
 scalar_t__ inl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int snd_ali_5451_peek(struct snd_ali *codec,
					     unsigned int port)
{
	return (unsigned int)inl(ALI_REG(codec, port)); 
}