#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  i2c_slave_t ;
struct TYPE_2__ {int APB1ENR; int APB1LENR; } ;

/* Variables and functions */
 uintptr_t I2C1_BASE ; 
 uintptr_t I2C2_BASE ; 
 int /*<<< orphan*/  NVIC_EnableIRQ (int) ; 
 int /*<<< orphan*/  NVIC_SetPriority (int,int) ; 
 TYPE_1__* RCC ; 
 int RCC_APB1ENR_I2C1EN_Pos ; 
 int RCC_APB1LENR_I2C1EN_Pos ; 
 int /*<<< orphan*/  i2c_slave_init_helper (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void i2c_slave_init(i2c_slave_t *i2c, int irqn, int irq_pri, int addr) {
    int i2c_idx = ((uintptr_t)i2c - I2C1_BASE) / (I2C2_BASE - I2C1_BASE);
    #if defined(STM32F4) || defined(STM32F7)
    RCC->APB1ENR |= 1 << (RCC_APB1ENR_I2C1EN_Pos + i2c_idx);
    volatile uint32_t tmp = RCC->APB1ENR; // Delay after enabling clock
    (void)tmp;
    #elif defined(STM32H7)
    RCC->APB1LENR |= 1 << (RCC_APB1LENR_I2C1EN_Pos + i2c_idx);
    volatile uint32_t tmp = RCC->APB1LENR; // Delay after enabling clock
    (void)tmp;
    #endif

    i2c_slave_init_helper(i2c, addr);

    NVIC_SetPriority(irqn, irq_pri);
    NVIC_EnableIRQ(irqn);
}