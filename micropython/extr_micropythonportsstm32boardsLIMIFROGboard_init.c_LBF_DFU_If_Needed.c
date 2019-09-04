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
struct TYPE_5__ {int MEMRMP; } ;
struct TYPE_4__ {int /*<<< orphan*/  Pin; int /*<<< orphan*/  Pull; int /*<<< orphan*/  Mode; int /*<<< orphan*/  Speed; } ;
typedef  TYPE_1__ GPIO_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  BT_RST_PIN ; 
 int /*<<< orphan*/  BT_RST_PORT ; 
 int /*<<< orphan*/  CONN_POS10_PIN ; 
 int /*<<< orphan*/  CONN_POS10_PORT ; 
 int /*<<< orphan*/  GPIO_HIGH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_MODE_INPUT ; 
 int /*<<< orphan*/  GPIO_MODE_OUTPUT_PP ; 
 int /*<<< orphan*/  GPIO_NOPULL ; 
 int /*<<< orphan*/  GPIO_PULLUP ; 
 int /*<<< orphan*/  GPIO_SPEED_FREQ_LOW ; 
 int /*<<< orphan*/  HAL_GPIO_Init (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ IS_GPIO_RESET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* SYSCFG ; 
 int /*<<< orphan*/  __HAL_RCC_GPIOB_CLK_ENABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_GPIOC_CLK_ENABLE () ; 

__attribute__((used)) static void LBF_DFU_If_Needed(void)
{


 GPIO_InitTypeDef GPIO_InitStruct;


   // Initialize and assert pin BTLE_RST
   // (hw reset to BLE module, so it won't drive UART3)

    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Pin = BT_RST_PIN;
    HAL_GPIO_Init(BT_RST_PORT, &GPIO_InitStruct);

    GPIO_HIGH(BT_RST_PORT, BT_RST_PIN); // assert BTLE reset


 /* -- Bootloader will be called if position 10 on the extension port
       is actively pulled low -- */
       // Note - this is an arbitrary choice, code could be modified to
       // monitor another GPIO of the STM32 and/or decide that active level
       // is high rather than low


    // Initialize Extension Port Position 10 = PB8 (bears I2C1_SCL)
    // Use weak pull-up to detect if pin is externally pulled low

    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Pin = CONN_POS10_PIN;
    HAL_GPIO_Init(CONN_POS10_PORT, &GPIO_InitStruct);

    // If selection pin pulled low...
    if ( IS_GPIO_RESET(CONN_POS10_PORT, CONN_POS10_PIN ))

    {
        // Remap bootloader ROM (ie System Flash) to address 0x0
        SYSCFG->MEMRMP = 0x00000001;

        // Init stack pointer with value residing at ROM base
    asm (
        "LDR     R0, =0x00000000\n\t"  // load ROM base address"
        "LDR     SP,[R0, #0]\n\t"      // assign main stack pointer"
        );

        // Jump to address pointed by 0x00000004 -- */

    asm (
        "LDR     R0,[R0, #4]\n\t"      // load bootloader address
        "BX      R0\n\t"
        );

    }
}